#ifndef PARSER_H
#define PARSER_H

#include <QDomDocument>

class Parser
{
public:
    Parser();
    ~Parser();

    void parse( const QString content );

    void findAttribiutes(const QString content, int index, QDomElement &element);

    inline QDomDocument page() const { return _page; }

    QDomNode createNode(const QString content, int index, QDomNode currentNode);
    QDomComment createComment(const QString content, int &index);

    QString tagName(const QString content, int &index );
    QString tagValue(const QString content, int index );
    QString tagComment(const QString content, int &index );
    QString attributeName(const QString content, int index );
    QString attributeValue(const QString content, int index );
    QString scriptContent(const QString content, int &index);

private:
    QDomDocument _page;
};

#endif // PARSER_H
