#if !defined(lloberon_module_out_h)
#define lloberon_module_out_h

	#if defined(__cplusplus)
		extern "C" {
	#endif

	void Out_WriteCh(char ch);
	void Out_WriteInt(int x, int n);
	void Out_WriteLn();
	void Out_Init_Module();

	void Out_set_output(void (*write)(char ch));
	void Out_reset_output();

	#if defined(__cplusplus)
		}
	#endif

#endif