#include "test_o_document.h"
#include <TestFramework/test.h>
#include "../src/o_document.h"
#include "../src/o_document_value.h"
#include <string.h>
#include <stdio.h>
#include "../src/o_memory.h"
void test_o_document_new()
{
	struct o_document * doc = o_document_new();
	o_document_free(doc);
}

void test_o_document_property_managment()
{
	struct o_document * doc = o_document_new();
	o_document_field_set(doc, "prova", o_document_value_int(30));
	o_document_field_set(doc, "prova1", o_document_value_int(31));
	int names_count;
	char ** names = o_document_field_names(doc, &names_count);
	assert_true(names_count == 2, "the number of names not is the same of insert");
	assert_true(strcmp(names[0], "prova") == 0, "the first name not is the same of insert");
	assert_true(strcmp(names[1], "prova1") == 0, "the second name not is the same of insert");
	int values_count;
	struct o_document_value ** values = o_document_field_values(doc, &values_count);
	assert_true(values_count == 2, "the number of values not is the same of insert");
	assert_true(o_document_value_get_int(values[0]) == 30, "the first value not is the same of insert");
	assert_true(o_document_value_get_int(values[1]) == 31, "the second value not is the same of insert");
	struct o_document_value * val1 = o_document_field_get(doc, "prova");
	assert_true(o_document_value_get_int(val1) == 30, "the get of value of key 'prova' fail ");
	struct o_document_value * val2 = o_document_field_get(doc, "prova1");
	assert_true(o_document_value_get_int(val2) == 31, "the get of value of key 'prova1' fail ");
	o_document_free(doc);
}

void test_o_document_serialize()
{
	struct o_document * doc = o_document_new();
	o_document_field_set(doc, "boolVal", o_document_value_bool(1));
	o_document_field_set(doc, "stringVal", o_document_value_string("popo"));
	struct o_string_buffer * buff = o_string_buffer_new();
	o_document_serialize(doc, buff);
	char * content = o_string_buffer_str(buff);
	assert_true(strcmp(content, "boolVal:true,stringVal:\"popo\"") == 0, "the serialization not is the expected");
	o_free(content);
	o_string_buffer_free(buff);
	o_document_free(doc);
}

void test_o_document_serialize_deserialize()
{
	struct o_document * doc = o_document_new();
	o_document_field_set(doc, "boolVal", o_document_value_bool(1));
	o_document_field_set(doc, "stringVal", o_document_value_string("popo"));
	struct o_string_buffer * buff = o_string_buffer_new();
	o_document_serialize(doc, buff);
	char * content = o_string_buffer_str(buff);
	struct o_input_stream * os = o_input_stream_new_bytes((unsigned char *) content, strlen(content));
	o_document_free(doc);
	doc = o_document_new();
	printf("%s","ser ");
	fflush(stdout);
	o_document_deserialize(doc, os);
	printf("%s"," after der");
	fflush(stdout);
	//assert_true(strcmp(content, "boolVal:true,stringVal:\"popo\"") == 0, "the serialization not is the expected");
	o_free(content);
	struct o_document_value *v = o_document_field_get(doc, "boolVal");
	assert_true(o_document_value_get_bool(v) == 1, "the boolean value failed after serialization");
	v = o_document_field_get(doc, "stringVal");
	assert_true(strcmp(o_document_value_get_string(v), "popo") == 0, "the string value failed after serialization");
	o_string_buffer_free(buff);
	o_document_free(doc);
	o_input_stream_free(os);

}

void o_document_suite()
{
	ADD_TEST(test_o_document_new, "test a simple o_document new and free");
	ADD_TEST(test_o_document_property_managment, "test property  management on o_document ");
	ADD_TEST(test_o_document_serialize, "test o_document native serialization");
	ADD_TEST(test_o_document_serialize_deserialize, "test a base o_document native serialization and deserialization");

}

