<?php include "includes/auth_guard.php"; ?>
<?php
error_reporting(E_ALL);

echo "<h2>TCP/IP Connection</h2>\n";

/* Create a TCP/IP socket. */
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
  echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
} else {
  echo "OK.\n";
}
$address = "127.0.0.1";
$service_port = 2500;
echo "Attempting to connect to '$address' on port '$service_port'...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
  echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
  echo "OK.\n";
}

$in = "G-3\r\n";

socket_write($socket, $in, strlen($in));

echo "Closing socket...";
socket_close($socket);
echo "OK.\n\n";
?>
<script>
  window.close();
</script>
