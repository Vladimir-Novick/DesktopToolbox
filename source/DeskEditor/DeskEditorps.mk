
DeskEditorps.dll: dlldata.obj DeskEditor_p.obj DeskEditor_i.obj
	link /dll /out:DeskEditorps.dll /def:DeskEditorps.def /entry:DllMain dlldata.obj DeskEditor_p.obj DeskEditor_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DeskEditorps.dll
	@del DeskEditorps.lib
	@del DeskEditorps.exp
	@del dlldata.obj
	@del DeskEditor_p.obj
	@del DeskEditor_i.obj
