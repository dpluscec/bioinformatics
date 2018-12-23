//
// Created by dplus on 18.12.2018..
//

#include "fasta_entry.h"

FastaEntry::FastaEntry(std::string &node_id, std::string &value, bool is_conting) {
  entry_id_ = node_id;
  value_ = value;
  length_ = value.length();
  is_conting_ = is_conting;
}

std::string FastaEntry::GetEntryId() {
  return entry_id_;
}

long FastaEntry::GetLength() {
  return length_;
}

bool FastaEntry::IsConting() {
  return is_conting_;
}
