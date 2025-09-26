.macro glabel label
	.global \label
	.type \label, @function
	\label:
.endm

.macro dlabel label
	.global \label
	\label:
.endm

.macro jlabel label
	.global \label
	\label:
.endm

.macro .fn name, visibility=global
.\visibility "\name"
.type "\name", @function
"\name":
.endm

.macro .endfn name
.size "\name" . - "\name"
.endm

.macro .obj name, visibility=global
.\visibility "\name"
.type "\name", @object
"\name":
.endm

.macro .endobj name
.size "\name", . - "\name"
.endm

.macro .sym name, visibility=global
.\visibility "\name"
"\name":
.endm

.macro .endsym name
.size "\name", . - "\name"
.endm
