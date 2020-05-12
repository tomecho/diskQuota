FROM alpine

RUN apk update && apk add gcc make sqlite-dev

WORKDIR /app
COPY . .

RUN make