FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-default \
    libqt5sql5-sqlite \
    sqlite3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && qmake ../server/server.pro && make -j$(nproc)

EXPOSE 12345

CMD ["./build/server"] 