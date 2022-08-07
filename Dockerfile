# syntax=docker/dockerfile:1
FROM ubuntu:latest
RUN apt-get update && \
      apt-get -y install sudo

RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo
RUN sudo apt-get update -y

RUN sudo apt-get install -y python3-pip
RUN apt-get install -y libsdl2-dev
RUN pip3 install conan
WORKDIR /app
COPY . .
# RUN yarn install --production
# CMD ["node", "src/index.js"]
# EXPOSE 3000