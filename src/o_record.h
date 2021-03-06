#ifndef O_RECORD_H_
#define O_RECORD_H_
#include "o_record_id.h"
#include "o_output_stream.h"
#include "o_input_stream.h"

/**
 * The record.
 */
struct o_record;

/*! \brief Retrieve the record id of record.
 *
 * \param record where retrive id.
 * \return the record id.
 */
struct o_record_id * o_record_get_id(struct o_record * record);

/*! \brief Retrieve the version of current record.
 *
 * \param the record where retrieve the version.
 * \return the version of record.
 */
int o_record_version(struct o_record * record);

/*! \brief Retrieve the type of record.
 *
 * \return the byte that describe the type of record.
 */
char o_record_type(struct o_record * record);

/*! \brief Serialize the record to output stream.
 *
 * \param record to write.
 * \param output where write;
 */
void o_record_serialize(struct o_record * record, struct o_output_stream * output);

/*! \brief fill a record whith deserialized data.
 *
 * \param record to fill.
 * \param output from read.
 */
void o_record_deserialize(struct o_record * record, struct o_input_stream * input);

/*! \brief Increase a reference to record.
 *
 * \param record to increase reference.
 */
void o_record_refer(struct o_record * record);

/*! \brief Decrease a reference to record.
 *
 * \param record to increase reference.
 */
void o_record_release(struct o_record * record);

#endif /* O_RECORD_H_ */
