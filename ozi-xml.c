#ifndef OZIXML_SINGLE_HEADER
#   include "ozi-xml.h"
#endif

#define _OZI_CHECK_ALLOC(ptr) if(ptr == NULL) { \
    fprintf(stderr, "FATAL: %s\n", "Got NULL on memory allocation, exiting..."); \
    exit(3); \
}

const char* Ozi__strdup(const char* string, size_t len)
{
    char* newstr = malloc(len + 1);
    _OZI_CHECK_ALLOC(newstr)
    strncpy(newstr, string, len);
    newstr[len] = '\0';
    return newstr;
}

Ozi_XmlNode* Ozi_XmlNode_new(void)
{
    Ozi_XmlNode* node = calloc(1, sizeof(Ozi_XmlNode));
    _OZI_CHECK_ALLOC(node)
    return node;
}

static size_t Ozi_Xml_parse_node(Ozi_XmlNode* node, const char* data)
{
    const char* reader = data;
    
    return reader - data;
}

Ozi_XmlNode* Ozi_Xml_parse(const char* data)
{
    Ozi_XmlNode* node = Ozi_XmlNode_new();
    while(*data) {
        switch(*data) {
            case '\n':
            case '\t':
            case ' ':
                ++data;
                break;
            case '<':
                if(data[1] && data[1] == '?') {
                    // skip the xml prolog
                    // todo add prolog skip.
                }
                else {
                    size_t node_presult = Ozi_Xml_parse_node(node, data);
                    if!(node_presult) {
                        return NULL;
                    } else 
                        data += node_presult;
                }
                break;
            default:
                // top level xml must be a tag
                fprintf(stderr, "SyntaxError: Expected <, got '%c'\n", *data);
                return NULL;
        }
    }
    return node;
}