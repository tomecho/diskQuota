FROM alpine

RUN apk update && apk add gcc make libc-dev sqlite-dev gdb

WORKDIR /app
COPY . .

RUN make diskQuota