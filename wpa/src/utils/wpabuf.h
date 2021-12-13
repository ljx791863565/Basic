#ifndef WPA_BUF_H
#define WAP_BUF_H


#define WPABUF_FLAG_EXT_DATA_BIT(0)


struct wpabuf {
    size_t size;
    size_t used;
    u8 *buf;
    unsigned int flags;
}

static inline size_t wpabuf_size(const struct wpabuf *buf)
{
    return buf->size;
}

static inline size_t wpabuf_len(const struct wpabuf *buf)
{
    return buf->used;
}

static inline size_t wpabuf_tailroom(const struct wpabuf *buf)
{
    return buf->size - buf->used;
}

static 
#endif //WAP_BUF_H