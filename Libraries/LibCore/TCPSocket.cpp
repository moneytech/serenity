/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <LibCore/TCPSocket.h>
#include <errno.h>
#include <sys/socket.h>

#ifndef SOCK_NONBLOCK
#    include <sys/ioctl.h>
#endif

namespace Core {

TCPSocket::TCPSocket(int fd, Object* parent)
    : Socket(Socket::Type::TCP, parent)
{
    // NOTE: This constructor is used by TCPServer::accept(), so the socket is already connected.
    m_connected = true;
    set_fd(fd);
    set_mode(IODevice::ReadWrite);
    set_error(0);
}

TCPSocket::TCPSocket(Object* parent)
    : Socket(Socket::Type::TCP, parent)
{
#ifdef SOCK_NONBLOCK
    int fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
#else
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;
    ioctl(fd, FIONBIO, &option);
#endif
    if (fd < 0) {
        set_error(errno);
    } else {
        set_fd(fd);
        set_mode(IODevice::ReadWrite);
        set_error(0);
    }
}

TCPSocket::~TCPSocket()
{
}

}
