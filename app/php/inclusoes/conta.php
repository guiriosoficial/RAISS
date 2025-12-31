<?php
include 'check.php';
include 'mysql.php';
include 'vars.php';
$link = conecta_mysql($servidor, $usuario, $senhadb, $db);
$nivel = procura_mysql($link, 'nivel', $tabela, $logado);
if ($nivel !== 2) {
  mysqli_close($link);
  echo "Erro usuário não tem permissão para acessar página\n";
  echo "<meta http-equiv='refresh' content='5;URL=\"/php/site.php\"'/>\n";
  exit(0);
}
$login_derr = "";
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
  if (!empty($login_d)) {
    if (!preg_match("/^[a-zA-Z0-9-_]+$/", $login_d)) {
      $login_derr = "Erro: Caracter Inválido.\n";
    }
    if (!in_db($link, $login_d) && empty($login_derr)) {
      $login_derr = "Erro: Usuário não existe.\n";
    }
    if (empty($login_derr)) {
      del_user_db($link, $login_d);
    }
  }
}
if ($_POST['login'] != NULL) {
  if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $login_err = "";
    if (!preg_match("/^[a-zA-Z0-9-_]+$/", $login)) {
      $login_err = "Erro: Caracter Inválido.\n";
    }
    if (!in_db($link, $login) && empty($login_err)) {
      $login_err = "Erro: Usuário não existe.\n";
    }
    if (empty($login_err)) {
      mysqli_real_query($link, "UPDATE $tabela  SET tentativas = 0 WHERE login = '$login'");
      if ($lv == '2' || $lv == '1') {
        if (!empty($login)) {
          mysqli_real_query($link, "UPDATE $tabela  SET nivel = $lv WHERE login = '$login'");
        }
      }
      if ($ativa == '1' || $ativa == '0') {
        if (!empty($login)) {
          mysqli_real_query($link, "UPDATE $tabela  SET ativo = $ativa WHERE login = '$login'");
        }
      }
    }
  }
}
if ($_POST['login_a'] != NULL) {
  $senha_aerr = $login_aerr = $confirm_aerr = "";
  if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (!empty($login_a)) {
      if (!preg_match("/^[a-zA-Z0-9-_]+$/", $login_a)) {
        $login_aerr = "Erro: Caracter Inválido.\n";
      }
      if (in_db($link, $login_a)) {
        $login_aerr = "Erro: Nome de usuário '$login_a' já existe.\n";
      }
    } else {
      $login_aerr = "Erro: Campo login não pode estar vazio.\n";
    }
    if (empty($senha)) {
      $senha_aerr = "Erro: Campo senha não pode estar vazio.\n";
    }
    if ($confirm !== $senha) {
      $confirm_aerr = "Erro: Senhas não coincidem.\n";
    }
    if (empty($login_aerr) && empty($senha_aerr) && empty($confirm_aerr)) {
      $comando = "INSERT INTO usuarios ( login , senha , cadastro ) VALUES ( '$login_a' , '$senhaSH' , NOW() )";
      if (!mysqli_real_query($link, $comando)) {
        if ($link->errno == "1062") {
          $login_aerr = "Erro: Nome de usuário '$login_a' já existe.\n";
        }
      }
    }
  }
}
?>
