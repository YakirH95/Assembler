#pragma once

dictionary* create_dictionary();
void delete_dictionary(dictionary* d);
void add_entry(dictionary* d, char* k, char* v);
char* get_value(dictionary* d, char* key);
