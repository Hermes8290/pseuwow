#include "MPQFile.h"

// MPQ file to be opened
MPQFile::MPQFile(const char *fn)
{
    _mpq = NULL;
    _isopen = SFileOpenArchive(fn,0,0,&_mpq);
}

bool MPQFile::HasFile(char *fn)
{
    return SFileHasFile(_mpq,fn);
}

// get size of a file within an mpq archive
ByteBuffer MPQFile::ReadFile(char *fn)
{
    ByteBuffer bb;
    HANDLE fh;
    if(!SFileOpenFileEx(_mpq, fn, 0, &fh))
        return bb;
    uint32 size = SFileGetFileSize(fh);
    bb.resize(size);
    SFileReadFile(fh, (void*)bb.contents(), size, NULL, NULL);
    return bb;
}

uint32 MPQFile::GetFileSize(char *fn)
{
    HANDLE fh;
    if(!SFileOpenFileEx(_mpq, fn, 0, &fh))
        return 0;
    uint32 size = SFileGetFileSize(fh);
    SFileCloseFile(fh);
    return size;
}