SET VcpkRoot=%~1
SET OutDir=%~2

xcopy /Y "%VcpkRoot%bin\glfw3.dll" "%OutDir%"