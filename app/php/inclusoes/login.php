<?php
include 'mysql.php';
include 'vars.php';
session_start();
$link = conecta_mysql($servidor, $usuario, $senhadb, $db);
$tentativas = procura_mysql($link, 'tentativas', $tabela, $login);
$ativo = procura_mysql($link, 'ativo', $tabela, $login);
if ($tentativas === NULL || $ativo === NULL) {
  mysqli_close($link);
  header("location:/");
}
if ($tentativas >= 5) {
  mysqli_close($link);
  echo "<meta http-equiv='refresh' content='3;URL=\"/\"'/>\n";
  echo "Numero de tentativas excedidas.<br>\n";
  exit(0);
}
if ($ativo === 0) {
  mysqli_close($link);
  echo "<meta http-equiv='refresh' content='3;URL=\"/\"'/>\n";
  echo "Usuario Inativo.<br>\n";
  exit(0);
}
if ($tentativas < 5 && $ativo == 1) {
  if (mysqli_real_query($link, "SELECT * FROM $tabela WHERE login = '$login' AND senha = '$senhaSH'")) {
    if ($result = mysqli_store_result($link)) {
      echo $result->num_rows;
      if ($result->num_rows > 0) {
        $_SESSION['login'] = $login;
        $_SESSION['senha'] = $senha;
        mysqli_real_query($link, "UPDATE $tabela  SET tentativas = 0 WHERE login = '$login' AND senha = '$senhaSH'");
        mysqli_close($link);
        header("location:/php/controle.php");
      } else {
        mysqli_real_query($link, "UPDATE $tabela SET tentativas = tentativas + 1 WHERE login = '$login'");
        mysqli_close($link);
        header("location:/");
      }
      mysqli_free_result($result);
    }
  }
} else {
  mysqli_close($link);
  header("location:/");
}
?>
