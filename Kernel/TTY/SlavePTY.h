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

#pragma once

#include <Kernel/FileSystem/InodeIdentifier.h>
#include <Kernel/TTY/TTY.h>

namespace Kernel {

class MasterPTY;

class SlavePTY final : public TTY {
public:
    virtual ~SlavePTY() override;

    void on_master_write(const UserOrKernelBuffer&, ssize_t);
    unsigned index() const { return m_index; }

    time_t time_of_last_write() const { return m_time_of_last_write; }

private:
    // ^TTY
    virtual String tty_name() const override;
    virtual ssize_t on_tty_write(const UserOrKernelBuffer&, ssize_t) override;
    virtual void echo(u8) override;

    // ^CharacterDevice
    virtual bool can_read(const FileDescription&, size_t) const override;
    virtual KResultOr<size_t> read(FileDescription&, size_t, UserOrKernelBuffer&, size_t) override;
    virtual bool can_write(const FileDescription&, size_t) const override;
    virtual const char* class_name() const override { return "SlavePTY"; }
    virtual KResult close() override;

    friend class MasterPTY;
    SlavePTY(MasterPTY&, unsigned index);

    RefPtr<MasterPTY> m_master;
    time_t m_time_of_last_write { 0 };
    unsigned m_index { 0 };
    char m_tty_name[32];
};

}
