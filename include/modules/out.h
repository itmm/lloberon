#if !defined(lloberon_module_out_h)
#define lloberon_module_out_h

	#if defined(__cplusplus)
		extern "C" {
	#endif

	void WriteCh(char ch);
	void WriteInt(int x, int n);
	void WriteLn();
	void Init_Module();

	void set_output(void (*write)(char ch));
	void reset_output();

	#if defined(__cplusplus)
		}
	#endif

#endif