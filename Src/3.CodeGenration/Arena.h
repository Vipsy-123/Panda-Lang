class ArenaAllocator{
    size_t size;
    byte* buff;
    byte* offset;
    
public:
    ArenaAllocator(size_t size){
        this->size=size;
        buff= static_cast<byte*>(malloc(size));
        offset=buff;
    }

    template<typename T>
    T* alloc(){
        void* curOffset=offset;
        offset+=sizeof(T);
        return static_cast<T*>(curOffset);
    }
    ArenaAllocator(ArenaAllocator &other)=delete;
    ArenaAllocator operator=(ArenaAllocator &other)=delete;
    ~ArenaAllocator(){
        free(buff);
    }
};