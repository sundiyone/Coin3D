#ifndef COIN_SBBYTEBUFFER_H
#define COIN_SBBYTEBUFFER_H

#include <memory>
#include <cstring>
#include <Inventor/SbBasic.h>

class COIN_DLL_API SbByteBuffer
{
public:
  SbByteBuffer(const char * buffer);
  SbByteBuffer(const SbByteBuffer & buffer);
  SbByteBuffer(size_t size = 0, const char * buffer = nullptr);
  SbByteBuffer(size_t size, const unsigned char * buffer);
  ~SbByteBuffer();

  bool isValid() const;

  size_t size() const;

  bool empty() const;

  const char & operator[](size_t idx) const;

  SbByteBuffer & operator=(const SbByteBuffer & in);

  bool operator==(const SbByteBuffer & that) const;

  SbByteBuffer & operator+=(const SbByteBuffer & buf) {
    this->push(buf);
    return *this;
  }

  void push(const SbByteBuffer & buf);

  const char * constData() const;
  char * data();

  static SbByteBuffer & invalidBuffer();
  void makeUnique();

private:
  size_t size_;
  std::shared_ptr<char> buffer;
  bool invalid;
  static SbByteBuffer invalidBuffer_;
};

inline void
SbByteBuffer::makeUnique()
{
  if (this->size_ && !this->buffer.unique()) {
    std::shared_ptr<char> tmp_buffer(std::unique_ptr<char[]>(new char [this->size_]));
    memcpy(tmp_buffer.get(),this->buffer.get(),this->size_);
    this->buffer=tmp_buffer;
  }
}

inline
SbByteBuffer::SbByteBuffer(size_t size_in, const unsigned char * buffer_in)
: size_(size_in),
  buffer(size_in
	 ? std::shared_ptr<char>(std::unique_ptr<char[]>(new char[size_in]))
	 : std::shared_ptr<char>(nullptr)),
  invalid(false)
{
  if (buffer_in)
    memcpy(this->buffer.get(),buffer_in,size_in);
}

inline
SbByteBuffer::SbByteBuffer(const SbByteBuffer & buffer) 
  : size_(buffer.size_),
    buffer(buffer.buffer),
    invalid(buffer.invalid)
{
}

inline
SbByteBuffer::SbByteBuffer(size_t size_in, const char * buffer_in)
: size_(size_in),
  buffer(size_in
	 ? std::shared_ptr<char>(std::unique_ptr<char[]>(new char[size_in]))
	 : std::shared_ptr<char>(nullptr)),
  invalid(false)
{
  if (buffer_in)
    memcpy(this->buffer.get(),buffer_in,size_in);
}

inline SbByteBuffer::SbByteBuffer(const char * buffer_in)
: size_(buffer_in?strlen(buffer_in)+1:0),
  buffer(size_
	 ? std::shared_ptr<char>(std::unique_ptr<char[]>(new char[size_]))
	 : std::shared_ptr<char>(nullptr)),
  invalid(false)
{
  if (buffer_in)
    memcpy(this->buffer.get(),buffer_in,this->size_);
}

inline SbByteBuffer::~SbByteBuffer()
{
}

inline bool
SbByteBuffer::isValid() const
{
  return !this->invalid;
}

inline size_t
SbByteBuffer::size() const
{
  return this->size_;
}

inline bool
SbByteBuffer::empty() const
{
  return size() == 0;
}

inline const char &
SbByteBuffer::operator[](size_t idx) const
{
  return this->constData()[idx];
}

inline SbByteBuffer &
SbByteBuffer::operator=(const SbByteBuffer & that)
{
  if (this != &that)
  {
    this->size_   = that.size_;
    this->buffer  = that.buffer;
    this->invalid = that.invalid;
  }
  return *this;
}


inline bool
SbByteBuffer::operator==(const SbByteBuffer & that) const
{
  size_t n = this->size();
  if (that.size() != n)
    return false;
  for (int i = n-1; i >= 0; --i) {
    if (this->constData()[i] != that.constData()[i])
      return false;
  }
  return true;
  
}

inline void
SbByteBuffer::push(const SbByteBuffer & that)
{
  SbByteBuffer n_buf(this->size()+that.size());
  memcpy(n_buf.data(),this->constData(),this->size());
  memcpy(&n_buf.data()[this->size()],that.constData(),that.size());
  *this=n_buf;
}

inline const char *
SbByteBuffer::constData() const
{
  return this->buffer.get();
}

inline char *
SbByteBuffer::data()
{
  this->makeUnique();
  return this->buffer.get();
}

inline SbByteBuffer &
SbByteBuffer::invalidBuffer()
{
  //FIXME: Do this once BFG 20080219
  SbByteBuffer::invalidBuffer_.invalid = true;
  return SbByteBuffer::invalidBuffer_;
}

#endif // !COIN_SBBYTEBUFFER_H
