cmake_minimum_required(VERSION 3.5)
project(cmsc23300 C)

set(CMAKE_C_STANDARD 11)

include_directories(samples/dispatch_table)

# Sockets/pthread samples
add_executable(client sockets/client.c)

add_executable(client-bomb sockets/client-bomb.c)

add_executable(oneshot-single sockets/oneshot-single.c)

add_executable(server-pthreads sockets/server-pthreads.c)
target_link_libraries(server-pthreads pthread)

add_executable(server-pthreads-mutex sockets/server-pthreads-mutex.c)
target_link_libraries(server-pthreads-mutex pthread)

add_executable(server-pthreads-condvar sockets/server-pthreads-condvar.c)
target_link_libraries(server-pthreads-condvar pthread)


# Dispatch table examples
add_executable(dispatch-int-one dispatch_table/dispatch-int-one.c dispatch_table/handlers.c)
add_executable(dispatch-int-two dispatch_table/dispatch-int-two.c dispatch_table/handlers.c)
add_executable(dispatch-str-one dispatch_table/dispatch-str-one.c dispatch_table/handlers.c)
add_executable(dispatch-str-two dispatch_table/dispatch-str-two.c dispatch_table/handlers.c)
