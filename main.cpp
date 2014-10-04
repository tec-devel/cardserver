#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<uriparser/Uri.h>

#include "NetworkController.h"

#include "PlayerObject.h"
#include "TableObject.h"

#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo jerry</body></html>"

#define SOP_HEADER "Access-Control-Allow-Origin\0"

#include <iostream>
#include <sstream>

struct PutData
{
    std::string reply;
};

static std::vector<std::string> parseRestfulData(const char * url)
{
    UriParserStateA state;
    UriUriA uri;

    state.uri = &uri;
    if (uriParseUriA(&state, url) != URI_SUCCESS)
    {
        /* Failure */
        uriFreeUriMembersA(&uri);
    }

    std::stringstream test(uri.pathHead->text.first);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(test, segment, '/'))
    {
        seglist.push_back(segment);
    }

    uriFreeUriMembersA(&uri);

    return seglist;
}

static int ahc_echo(void * cls,
                    struct MHD_Connection * connection,
                    const char * url,
                    const char * method,
                    const char * version,
                    const char * upload_data,
                    size_t * upload_data_size,
                    void ** ptr)
{
    static int dummy;
    const char * page = (const char*) cls;
    struct MHD_Response * response;
    int ret;

    static PutData pd;

    if (strcmp(method, "GET") == 0)
    {
        if (&dummy != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &dummy;
            return MHD_YES;
        }

        if (0 != *upload_data_size)
            return MHD_NO; /* upload data in a GET!? */
        *ptr = NULL; /* clear context pointer */

        //        MHD_add_response_header(response, SOP_HEADER, "*\0");

        std::vector<std::string> seglist = parseRestfulData(url);

        if (!seglist.empty())
        {
            std::string reply;
            std::string request;
            NetworkController::instance()->methodGet(seglist[0], seglist, request, &reply);
            response = MHD_create_response_from_data(reply.size(), (void*) reply.data(), MHD_NO, MHD_NO);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            std::cout << reply << std::endl;
        }
        else
        {
            response = MHD_create_response_from_data(strlen(page), (void*) page, MHD_NO, MHD_NO);
            ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        }


        MHD_destroy_response(response);
    }
    else if (strcmp(method, "POST") == 0)
    {
        if (&pd != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &pd;
            return MHD_YES;
        }

        if (0 != *upload_data_size)
        {
            std::vector<std::string> restful_data = parseRestfulData(url);
            if (!restful_data.empty())
            {
                std::string request;
                NetworkController::instance()->methodPost(restful_data[0], restful_data, request, &pd.reply);
                std::cout << "POST RESPONCE " << pd.reply << std::endl;
            }

            *upload_data_size = 0;

            return MHD_YES;
        }

        *ptr = NULL; /* clear context pointer */

        response = MHD_create_response_from_data(pd.reply.size(), (void*) pd.reply.data(), MHD_NO, MHD_YES);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);        

        pd.reply.clear();
        MHD_destroy_response(response);
    }
    else if (strcmp(method, "PUT") == 0)
    {
        if (&pd != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &pd;
            return MHD_YES;
        }

        if (0 != *upload_data_size)
        {
            std::vector<std::string> restful_data = parseRestfulData(url);

            if (!restful_data.empty())
            {
                std::string upload_data_str;

                if (upload_data)
                    upload_data_str.append(upload_data, *upload_data_size);

                NetworkController::instance()->methodPut(restful_data[0], restful_data, upload_data_str, &pd.reply);
                std::cout << "PUT RESPONCE " << pd.reply << std::endl;
            }

            *upload_data_size = 0;
            return MHD_YES;
        }

        *ptr = NULL; /* clear context pointer */

        response = MHD_create_response_from_data(pd.reply.size(), (void*) pd.reply.data(), MHD_NO, MHD_YES);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                        
        pd.reply.clear();
        MHD_destroy_response(response);
    }
    else if (strcmp(method, "DELETE") == 0)
    {
        if (&dummy != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &dummy;
            return MHD_YES;
        }

        *ptr = NULL; /* clear context pointer */
        response = MHD_create_response_from_data(strlen(page), (void*) 0, MHD_NO, MHD_NO);

        std::vector<std::string> restful_data = parseRestfulData(url);

        if (!restful_data.empty())
        {
            NetworkController::instance()->methodDelete(restful_data[0], restful_data);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        }
        else
        {
            ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        }

        MHD_destroy_response(response);
    }
    else
        return MHD_NO; /* unexpected method */

    return ret;
}

int main(int argc,
         char ** argv)
{
    struct MHD_Daemon * d;
    if (argc != 2)
    {
        printf("%s PORT\n",
               argv[0]);
        return 1;
    }


    NetworkController::instance()->registerObject(new PlayerObject(std::string("player")));
    NetworkController::instance()->registerObject(new TableObject(std::string("table")));

    d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                         atoi(argv[1]),
                         NULL,
                         NULL,
                         &ahc_echo,
                         (void*) PAGE,
                         MHD_OPTION_END);

    //        d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
    //                         atoi(argv[1]),
    //                         NULL,
    //                         NULL,
    //                         &ahc_echo,
    //                         (void*) PAGE,
    //                         MHD_OPTION_END);

    if (d == NULL)
        return 1;
    (void) getchar();
    MHD_stop_daemon(d);
    return 0;
}
