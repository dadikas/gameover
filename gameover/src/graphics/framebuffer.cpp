#include "gameover/graphics/framebuffer.h"

#include "gameover/log.h"

#include "glad/glad.h"

namespace gameover::graphics {
	Framebuffer::Framebuffer(uint32_t width, uint32_t height)
		: mFbo(0)
		, mTextureId(0)
		, mRenderbufferId(0)
		, mWith(width)
		, mHeight(height)
		, mCCR(1), mCCG(1), mCCB(1), mCCA(1)
	{
		glGenFramebuffers(1, &mFbo);
		glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

		//create colour texture
		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWith, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureId, 0);


		//create depth/stencil renderbuffer
		glGenRenderbuffers(1, &mRenderbufferId); 
		glBindRenderbuffer(GL_RENDERBUFFER, mRenderbufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWith, mHeight); 
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderbufferId); 

		int32_t completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (completeStatus != GL_FRAMEBUFFER_COMPLETE) {
			GAMEOVER_ERROR("Failure to create framebuffer. Complete status: {}", completeStatus);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &mFbo);
		mFbo = 0;
		mTextureId = 0;
		mRenderbufferId = 0;
	}
}