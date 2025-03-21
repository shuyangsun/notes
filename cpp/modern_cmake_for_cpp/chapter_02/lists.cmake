cmake_minimum_required(VERSION 3.26)

set(LIST_1 this is a list)
set(LIST_2 "this;is;also;a;list")
set(LIST_3 here is "another;list")

message(${LIST_1}) # thisisalist
message(${LIST_2}) # thisisalsoalist
message(${LIST_3}) # hereisanotherlist

list(LENGTH LIST_1 LIST_1_LEN)
message(${LIST_1_LEN}) # 4
