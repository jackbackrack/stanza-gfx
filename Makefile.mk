${GEN}/gl.pkg: stanza-gfx/gl.stanza ${GEN}/utils.pkg 
	stanza $< $(STZ_FLAGS) -pkg ${GEN}

${GEN}/glu.pkg: stanza-gfx/glu.stanza ${GEN}/gl.pkg ${GEN}/geom.pkg 
	stanza $< $(STZ_FLAGS) -pkg ${GEN}

${GEN}/glfw.pkg: stanza-gfx/glfw.stanza ${GEN}/utils.pkg ${GEN}/gl.pkg 
	stanza $< $(STZ_FLAGS) -pkg ${GEN}

${GEN}/font.pkg: stanza-gfx/font.stanza ${GEN}/utils.pkg ${GEN}/geom.pkg 
	stanza $< $(STZ_FLAGS) -pkg ${GEN}

${GEN}/gfx.pkg: stanza-gfx/gfx.stanza ${GEN}/gl.pkg ${GEN}/glfw.pkg ${GEN}/font.pkg 
	stanza $< $(STZ_FLAGS) -pkg ${GEN}

