/*
 * In this program, the usage of inotify(7) will be tested.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <assert.h>

#define SIZE_BUF 100

void print_event(uint32_t mask);

int
main(int argc, char** argv) {
  const char const* file_monitored = "./asdf";

  int fd_monitor = inotify_init1(0);
  if (fd_monitor == -1) {
    perror("inotify_init1()");
    exit(EXIT_FAILURE);
  }

  int desc = inotify_add_watch(fd_monitor, file_monitored, IN_ALL_EVENTS);
  if (desc == -1) {
    perror("inotify_add_watch()");
    exit(EXIT_FAILURE);
  }

  /*
   * add SIZE_BUF since event.name[] may have different lengths.
   * adjust SIZE_BUF as necessary.
   */
  size_t size_event = sizeof(struct inotify_event) + SIZE_BUF;
  struct inotify_event event;
  int bytes_read;
  while (1) {
    bytes_read = read(fd_monitor, &event, size_event);
    if (bytes_read == -1) {
      perror("read()");
      exit(EXIT_FAILURE);
    }
    assert(bytes_read <= size_event);
    print_event(event.mask);
  }

  return EXIT_SUCCESS;
}

void
print_event(uint32_t mask) {
  if (mask & IN_ACCESS) {
    printf("IN_ACCESS\n");
  }
  if (mask & IN_ATTRIB) {
    printf("IN_ATTRIB\n");
  }
  if (mask & IN_CLOSE_WRITE) {
    printf("IN_CLOSE_WRITE\n");
  }
  if (mask & IN_CLOSE_NOWRITE) {
    printf("IN_CLOSE_NOWRITE\n");
  }
  if (mask & IN_CREATE) {
    printf("IN_CREATE\n");
  }
  if (mask & IN_DELETE) {
    printf("IN_DELETE\n");
  }
  if (mask & IN_DELETE_SELF) {
    printf("IN_DELETE_SELF\n");
  }
  if (mask & IN_MODIFY) {
    printf("IN_MODIFY\n");
  }
  if (mask & IN_MOVE_SELF) {
    printf("IN_MOVE_SELF\n");
  }
  if (mask & IN_MOVED_FROM) {
    printf("IN_MOVED_FROM\n");
  }
  if (mask & IN_MOVED_TO) {
    printf("IN_MOVED_TO\n");
  }
  if (mask & IN_OPEN) {
    printf("IN_OPEN\n");
  }
}
