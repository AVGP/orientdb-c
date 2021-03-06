#ifndef O_STORAGE_REMOTE_H_
#define O_STORAGE_REMOTE_H_
#include "o_connection_remote.h"

struct o_storage_remote;

/**
 * Create a new instance of a remote storage.
 *
 * @param conn the remote connection.
 * @return the new storage instace.
 *
 */
struct o_storage * o_storage_remote_new(struct o_connection_remote * conn,char * name,char * username, char * password);

#endif /* O_STORAGE_REMOTE_H_ */
