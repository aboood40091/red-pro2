void sub_029F1A50(void* list, void* node)
{
    u32* list_words = static_cast<u32*>(list);
    u32* node_words = static_cast<u32*>(node);
    u32 old_head = list_words[0];
    list_words[0] = reinterpret_cast<u32>(node);
    node_words[1] = reinterpret_cast<u32>(list);
    node_words[0] = old_head;
    if (old_head != 0)
        *reinterpret_cast<u32*>(old_head + 4) = reinterpret_cast<u32>(node);
}

void sub_029F1A70(void* list, void*)
{
    u32* list_words = static_cast<u32*>(list);
    u32 head = list_words[0];
    if (head != 0)
    {
        u32 back = list_words[1];
        *reinterpret_cast<u32*>(head + 4) = back;
    }
    u32 link = list_words[1];
    if (link != 0)
        *reinterpret_cast<u32*>(link) = list_words[0];
    list_words[1] = 0;
    list_words[0] = 0;
}
