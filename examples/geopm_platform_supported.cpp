/*
 * Copyright (c) 2015, 2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY LOG OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <string.h>

#include "PlatformFactory.hpp"
#include "Platform.hpp"
#include "geopm_hash.h"


int main(int argc, char **argv)
{
    int err = 0;
    char error_msg[512];

    if (argc == 2 &&
        strncmp(argv[1], "crc32", strlen("crc32") + 1) == 0) {
        uint64_t result = geopm_crc32_u64(0xDEADBEEF, 0xBADFEE);
        if (result == 0xA347ADE3 ) {
            std::cout << "Platform supports crc32 intrinsic." << std::endl;
        }
        else {
            err = GEOPM_ERROR_PLATFORM_UNSUPPORTED;
            std::cerr << "Warning: Platform does not support crc32 intrinsic." << std::endl;
        }
    }
    else {
        try {
            geopm::PlatformFactory factory;
            geopm::Platform *platform = factory.platform("rapl");
            std::string plat_name;
            platform->name(plat_name);
            std::cout << "Platform \"" << plat_name << "\" supported by GEOPM runtime." << std::endl;
        }
        catch (geopm::Exception ex) {
            err = ex.err_value();
            geopm_error_message(err, error_msg, 512);
            std::cerr << "Warning: <geopm_platform_supported>: " << error_msg << "." << std::endl;
            if (err != GEOPM_ERROR_PLATFORM_UNSUPPORTED) {
                 err = 0;
            }
        }
    }
    return err;
}
