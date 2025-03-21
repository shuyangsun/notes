cmake_minimum_required(VERSION 3.26)

set(VAR 1)
message(${VAR}) # 1
block()
    set(VAR 2)
    message(${VAR}) # 2
    block()
        set(VAR 3)
        message(${VAR}) # 3
    endblock()
    message(${VAR}) # 2
endblock()
message(${VAR}) # 1
