FROM alpine

RUN apk update && apk add gcc make libc-dev sqlite-dev

WORKDIR /app
COPY . .

RUN make diskQuota