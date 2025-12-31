<?php
function test_input($input)
{
  $input = trim($input);
  $input = htmlspecialchars($input);
  return $input;
}

// POSTs
$login = test_input($_POST['login']);
$login_a = test_input($_POST['login_a']);
$login_d = test_input($_POST['login_d']);
$senha = test_input($_POST['senha']);
$confirm = test_input($_POST['confirm']);
$senhaSH = hash('sha256', $senha);
$ativa = $_POST['ativa'];
$lv = $_POST['nivel'];

// Self PHP
$self = $_SERVER["PHP_SELF"];

// Banco de Dados
$servidor = "localhost";
$usuario = "raiss";
$senhadb = "raiss";
$db = "raiss";
$tabela = "usuarios";
?>
