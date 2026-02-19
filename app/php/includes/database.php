<?php

function connectPDO(): PDO
{
    return new PDO(
        "mysql:host=localhost;dbname=raiss;charset=utf8",
        "raiss",
        "raiss",
        [
            PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC
        ]
    );
}

// =====================
// USERS
// =====================

function fetchUserField(PDO $pdo, string $field, string $username): ?int
{
    $stmt = $pdo->prepare(
        "SELECT $field FROM usuarios WHERE login = :login"
    );
    $stmt->execute(['login' => $username]);

    $value = $stmt->fetchColumn();
    return $value !== false ? (int) $value : null;
}

function userExists(PDO $pdo, string $username): bool
{
    $stmt = $pdo->prepare(
        "SELECT 1 FROM usuarios WHERE login = :login"
    );
    $stmt->execute(['login' => $username]);
    return $stmt->rowCount() > 0;
}

function deleteUser(PDO $pdo, string $username): void
{
    $stmt = $pdo->prepare(
        "DELETE FROM usuarios WHERE login = :login"
    );
    $stmt->execute(['login' => $username]);

    echo "<meta http-equiv='refresh' content='0'>";
}
