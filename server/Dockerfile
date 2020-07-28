FROM node:12.18.2-alpine

# Switch to non-root user
RUN adduser -D airpapyrus
USER airpapyrus
WORKDIR /home/airpapyrus

COPY --chown=airpapyrus:airpapyrus . .

RUN yarn rebuild

ENTRYPOINT yarn start
