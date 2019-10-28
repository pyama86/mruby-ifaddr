/*
** mrb_ifaddr.c - IFAddr class
**
** Copyright (c) pyama86 2019
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

static const struct mrb_data_type mrb_ifaddr_data_type = {
    "mrb_ifaddr_data",
    mrb_free,
};

static mrb_value mrb_ifaddr_get(mrb_state *mrb, mrb_value self)
{
  char *ifname;
  mrb_int len;
  int fd;
  struct ifreq ifr;

  mrb_get_args(mrb, "s", &ifname, &len);

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't get sock");
  }
  ifr.ifr_addr.sa_family = AF_INET;

  strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
  int ret = ioctl(fd, SIOCGIFADDR, &ifr);
  if (ret == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't get addr");
  }

  close(fd);
  return mrb_str_new_cstr(mrb, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}

void mrb_mruby_ifaddr_gem_init(mrb_state *mrb)
{
  struct RClass *ifaddr;
  ifaddr = mrb_define_class(mrb, "IFAddr", mrb->object_class);
  mrb_define_class_method(mrb, ifaddr, "get", mrb_ifaddr_get, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_ifaddr_gem_final(mrb_state *mrb)
{
}

