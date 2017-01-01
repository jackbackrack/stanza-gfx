ifeq ($(OS2), Darwin)
  LIBS += -lglfw3 -framework Carbon -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
  OS := $(strip $(shell uname -o))
  ifeq ($(OS), GNU/Linux)
    LIBS += -lglfw -lrt -lm -lXrandr -lXinerama -lXi -lXcursor -lXrender -lGL -lGLU -lpthread -ldl -ldrm -lXdamage -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-randr -lxcb-xfixes -lxcb-render -lxcb-shape -lxcb-sync -lxshmfence -lXxf86vm -lXext -lX11 -lxcb -lXau -lXdmcp
  endif
endif

stanza_gfx_all: ${GEN}/gl.pkg ${GEN}/glu.pkg ${GEN}/glfw.pkg ${GEN}/font.pkg ${GEN}/gfx.pkg 

ALL_PKG_DEPS += stanza_gfx_all

${GEN}/gl.pkg: stanza-gfx/gl.stanza ${GEN}/utils.pkg 
	stanza $< $(STZ_FLAGS)

${GEN}/glu.pkg: stanza-gfx/glu.stanza ${GEN}/gl.pkg ${GEN}/geom.pkg 
	stanza $< $(STZ_FLAGS)

${GEN}/glfw.pkg: stanza-gfx/glfw.stanza ${GEN}/utils.pkg ${GEN}/gl.pkg 
	stanza $< $(STZ_FLAGS)

${GEN}/font.pkg: stanza-gfx/font.stanza ${GEN}/utils.pkg ${GEN}/geom.pkg 
	stanza $< $(STZ_FLAGS)

${GEN}/gfx.pkg: stanza-gfx/gfx.stanza ${GEN}/gl.pkg ${GEN}/glfw.pkg ${GEN}/font.pkg 
	stanza $< $(STZ_FLAGS)

