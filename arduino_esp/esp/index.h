// clang-format off

String html = "<html>\n\r"
"\n\r"
"<body>\n\r"
"<script>\n\r"
"    function relay_1_click() {\n\r"
"        xhttp = new XMLHttpRequest()\n\r"
"        xhttp.open(\"GET\", \"/REL/1\", true)\n\r"
"        xhttp.send()\n\r"
"        console.log(\"rele 1\")\n\r"
"    }\n\r"
"\n\r"
"    function relay_2_click() {\n\r"
"        xhttp = new XMLHttpRequest()\n\r"
"        xhttp.open(\"GET\", \"/REL/2\", true)\n\r"
"        xhttp.send()\n\r"
"        console.log(\"rele 2\")\n\r"
"    }\n\r"
"</script>\n\r"
"    <button class=\"btn\" onclick=\"relay_1_click()\">РЕЛЕ 1</button>\r\n"
"    <button class=\"btn\" onclick=\"relay_2_click()\">РЕЛЕ 2</button>\n\r"
"</body>\n\r"
"\n\r"
"<style>\n\r"
"    .btn {\n\r"
"        width: 100px;\n\r"
"        height: 100px;\n\r"
"        border-radius: 20px;\n\r"
"        background-color: aqua;\n\r"
"        font-size: large;\n\r"
"    }\n\r"
"</style>\n\r"
"\n\r"
"</html>\n\r";
