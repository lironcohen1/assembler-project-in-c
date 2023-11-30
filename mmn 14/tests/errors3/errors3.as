; this file contain possible error in the pre assembler pass


MAIN: mov @r0   , @r2

;comment line
mcro m1      ERROR

	cmp 5   , +5
	
	
	;another comment line
	
	
endmcro

m1

mcro m2


END: stop 
endmcro   ERROR
