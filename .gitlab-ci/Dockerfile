# Wee need unstable for now because of check version
FROM debian:unstable

ENV HOME /root

RUN \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get -y install --no-install-recommends \
    autoconf autoconf-archive automake libtool \
    make pkg-config gcc \
    check cppcheck valgrind lcov \
    zip xz-utils \
    && \
  apt-get clean

CMD [ "bash" ]

# vim: ft=dockerfile
