#pragma once


dictionary* identify_labels(char* assembly_input);
void define_label(dictionary* label_dict, char* current_line, int IC);
