/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Microsoft Corporation
*
* -=- Robust Distributed System Nucleus (rDSN) -=-
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

/*
* Description:
*     message parser for browser-generated http request
*
* Revision history:
*     Feb. 2016, Tianyi Wang, first version
*     xxxx-xx-xx, author, fix bug about xxx
*/

#pragma once

# include <dsn/internal/ports.h>
# include <dsn/internal/rpc_message.h>
# include <dsn/internal/singleton.h>
# include <dsn/internal/message_parser.h>
# include <vector>
# include <queue>
# include "http_parser.h"

namespace dsn
{
    class http_message_parser : public message_parser
    {
    public:
        http_message_parser(int buffer_block_size, bool is_write_only);
        message_ex* get_message_on_receive(int read_length, /*out*/ int& read_next) override;

        int prepare_buffers_on_send(message_ex* msg, int offset, /*out*/ send_buf* buffers) override;

        int get_send_buffers_count(message_ex* msg) override;
    private:
        http_parser _parser;
        http_parser_settings _parser_setting;
        std::unique_ptr<message_ex> _current_message;
        std::queue<std::unique_ptr<message_ex>> _received_messages;
        enum
        {
            parsing_id,
            parsing_rpc_id,
            parsing_rpc_name,
            parsing_payload_format,
            parsing_nothing
        } response_parse_state;
        std::string request_header_send_buffer, response_header_send_buffer;
};
}