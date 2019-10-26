
DesktopToolboxps.dll: dlldata.obj DesktopToolbox_p.obj DesktopToolbox_i.obj
	link /dll /out:DesktopToolboxps.dll /def:DesktopToolboxps.def /entry:DllMain dlldata.obj DesktopToolbox_p.obj DesktopToolbox_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DesktopToolboxps.dll
	@del DesktopToolboxps.lib
	@del DesktopToolboxps.exp
	@del dlldata.obj
	@del DesktopToolbox_p.obj
	@del DesktopToolbox_i.obj
