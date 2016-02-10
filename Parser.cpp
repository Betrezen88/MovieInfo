#include "Parser.h"

#include <QDebug>

Parser::Parser()
{
    qDebug() << "Parser (" << this << ") object created.";
}

Parser::~Parser()
{
    qDebug() << "Parser (" << this << ") object destroyed.";
}

void Parser::parse(const QString content)
{
    QDomNode currentNode;

    for ( int i=0; i<content.size(); ++i ) {
        if ( content.at(i) == '<' ) {
            if ( content.at(i+1) == '/') {
                currentNode = currentNode.parentNode(); //zamknięcie '</'
            }
            else if ( content.at(i+1) == '!' && content.at(i+2) == '-' && content.at(i+3) == '-' ) {
                currentNode.appendChild( createComment(content, i) );
            }
            else {
                currentNode = createNode(content, i, currentNode);
            }
        }
        else if ( content.at(i) == '>') {
            if ( content.at(i-1) == '/' || currentNode.nodeName() == "meta" || currentNode.nodeName() == "link") {
                currentNode = currentNode.parentNode(); //zamknięcie '/>'
            }
            else if ( currentNode.nodeName() == "script" ) {
                currentNode.appendChild( _page.createTextNode(scriptContent(content, ++i)) );
            }
            else if ( i+1 < content.size()-1 ) {
                if ( content.at(i+1) == '<' ) {
                    continue;
                }
                else if ( !(content.at(i+1) == ' ' && content.at(i+2) == '<')) {
                    currentNode.appendChild( _page.createTextNode(tagValue(content, ++i)) );
                    //qDebug() << tagValue(content, ++i);
                }
            }
        }
    }
}

void Parser::findAttribiutes(const QString content, int index, QDomElement &element)
{
    QString name = ""; int i = index;
    while ( content.at(i) != '>' ) {
        if ( content.at(i) == ' ' )
            name = attributeName(content, ++i);
        else if ( content.at(i-1) == '=' && content.at(i) == '"' )
            element.setAttribute( name, attributeValue(content, ++i) );
        ++i;
    }
}

QDomNode Parser::createNode(const QString content, int index, QDomNode currentNode)
{
    int i = index;
    QDomElement element = _page.createElement( tagName(content, ++i) );
    findAttribiutes(content, i, element);
    if ( _page.childNodes().size() > 0 ) {
        currentNode.appendChild( element );
        currentNode = currentNode.lastChild();
    }
    else {
        _page.appendChild( element );
        currentNode = _page.lastChild();
    }
    return currentNode;
}

QDomComment Parser::createComment(const QString content, int &index)
{
    index+=4;
    QDomComment comment = _page.createComment( tagComment( content, index ) );
    return comment;
}

QString Parser::tagName(const QString content, int &index)
{
    QString name = "";
    while ( content.at(index) != ' ' && content.at(index) != '>' && content.at(index) != '/' )
        name += content.at(index++);
    return name;
}

QString Parser::tagValue(const QString content, int index)
{
    QString value = "";
    while ( content.at(index) != '<')
        value += content.at(index++);
    return value.simplified();
}

QString Parser::tagComment(const QString content, int &index)
{
    QString comment = "";
    while ( !(content.at(index) == '-' && content.at(index+1) == '-' && content.at(index+2) == '>') )
        comment += content.at(index++);
    ++index;
    return comment;
}

QString Parser::attributeName(const QString content, int index)
{
    QString name = "";
    while ( content.at(index) != '=' && content.at(index+1) != '"')
        name += content.at(index++);
    return name;
}

QString Parser::attributeValue(const QString content, int index)
{
    QString value = "";
    while ( content.at(index) != '"' )
        value += content.at(index++);
    return value.simplified();
}

QString Parser::scriptContent(const QString content, int &index)
{
    QString script = "";
    while ( !(content.at(index) == '<' && content.at(index+1) == '/' ) ) //&& content.at(index+2) == 's' && content.at(index+3) == 'c' && content.at(index+4) == 'r' && content.at(index+5) == 'i' && content.at(index+6) == 'p' && content.at(index+6) == 't'
        script += content.at(index++);
    --index;
    return script;
}
