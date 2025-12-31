FROM mattrayner/lamp:latest-1804

WORKDIR /app

COPY . /app

RUN apt-get update && apt-get install -y gcc

RUN gcc servidor.c -o servidor -lpthread

RUN mkdir -p /var/run/mysqld && \
    chown mysql:mysql /var/run/mysqld && \
    rm -rf /var/lib/mysql/* && \
    mysqld --initialize-insecure --user=mysql && \
    chown -R mysql:mysql /var/lib/mysql && \
    mysqld_safe & \
    until mysqladmin ping --silent; do \
      sleep 1; \
    done && \
    mysql -u root < /app/script.sql && \
    mysqladmin shutdown

EXPOSE 80 2500

CMD ["sh", "-c", "/app/servidor 2500 & /run.sh"]
