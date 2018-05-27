class StoragePool{

	using byte = char;

	public:
		virtual ~StoragePool();
		virtual void* Allocate( size_t ) = 0;
		virtual void Free( void * ) = 0;
};

struct Tag{ StoragePool * pool };

class SLPool : public StoragePool{
	public:
		struct Header
		{
			unsigned int m_lenght;
			Header() : m_lenght(0u);
		};

		struct Block : public Header{
			enum { BlockSize = 16 };

			union{
				Block *m_next;
				char m_raw[ BlockSize - sizeof(Header)];
			};

			Block() : Header(), m_next( nullptr ){ /* Empty */};
		};

	private:
		explicit SLPool( size_t );
		~SLPool();
		void * Allocate( size_t );
		void Free( void * );
		

};