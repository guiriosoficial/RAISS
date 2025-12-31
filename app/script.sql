CREATE DATABASE raiss;

USE raiss;

CREATE TABLE usuarios (
    id INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
    login VARCHAR(30) NOT NULL,
    senha VARCHAR(80) NOT NULL,
    nivel INT(1) UNSIGNED NOT NULL DEFAULT 1,
    ativo BOOL NOT NULL DEFAULT 0,
    tentativas INT(1) UNSIGNED NOT NULL DEFAULT 0,
    cadastro DATETIME NOT NULL,
    PRIMARY KEY ( id ),
    UNIQUE KEY login ( login )
)
DEFAULT CHARSET=utf8;

INSERT INTO usuarios (login, senha, nivel, ativo, cadastro)
VALUES ('admin', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', 2, 1, NOW());

CREATE USER 'raiss'@'localhost' IDENTIFIED BY 'raiss';
GRANT ALL PRIVILEGES ON raiss.* TO 'raiss'@'localhost' WITH GRANT OPTION;
FLUSH PRIVILEGES;
