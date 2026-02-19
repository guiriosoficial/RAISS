<?php 
include "includes/auth_guard.php";
error_reporting(E_ALL);
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
  echo "Erro: " . socket_strerror(socket_last_error());
  exit(0);
}
$address = "127.0.0.1";
$service_port = 2500;
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
  echo "Erro: ($result) " . socket_strerror(socket_last_error($socket));
  exit(0);
}

$in = "0\r\n";
socket_write($socket, $in, strlen($in));
socket_close($socket);
echo '<script>window.close();</script>';
header('location:../site.php');
?>
