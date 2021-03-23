#include <precomp.h>

#include "Texture.h"



Render::Texture::Texture(const std::string& name, Render::TextureType type)
	: m_Name(name.substr( name.find_last_of('/') + 1)), m_Type(type)
{	
	m_ID = LoadNativeTexture(name);
}

unsigned Render::Texture::GetID()
{
	return m_ID;
}

std::string Render::Texture::GetName()
{
	return m_Name;
}

Render::TextureType Render::Texture::GetType()
{
	return m_Type;
}



Render::RawImage Render::Texture::LoadRawImage( const std::string &name, int desiredChannels )
{    
    unsigned id;

    glGenTextures( 1, &id );
    glBindTexture( GL_TEXTURE_2D, id );

    int width, height, nChannels;

    unsigned char *data = stbi_load( name.c_str(), &width, &height, &nChannels, desiredChannels );	

	return { id, width, height, nChannels, data };
}

GLint Render::Texture::GetFormat( int nChannels )
{    
	switch ( nChannels )
    {
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        return GL_RED;
    }
}

void Render::Texture::BindTextureImage( GLenum target, RawImage& rawimage )
{
    auto [id, width, height, nChannels, data] = rawimage.Get();
    auto iForm = GetFormat( nChannels );

	BindTextureImage( target, id, width, height, iForm, data );
}

void Render::Texture::BindTextureImage( GLenum target, int id, int width, int height, GLint internalformat,
                                        const stbi_uc *data, GLenum format, GLint level, GLenum type, bool genmm )
{
    glBindTexture( GL_TEXTURE_2D, id );
    glTexImage2D( GL_TEXTURE_2D, level, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data );
    if (genmm)
		glGenerateMipmap( GL_TEXTURE_2D );
}

template<>
inline void Render::Texture::SetTexParam( GLenum target, GLenum pname, float param )
{
    glTexParameterf( target, pname, param );
}

template <> 
inline void Render::Texture::SetTexParam( GLenum target, GLenum pname, float* param )
{
    glTexParameterfv( target, pname, param );
}

unsigned Render::Texture::LoadNativeTexture( const std::string &name, GLenum target)
{		
	RawImage rawIm{ LoadRawImage( name ) };
	

	if ( rawIm.data == nullptr )
    {
        LOG_ERROR( "Failed to load texture\nTexture: {}", name );
        return 0;
    }

    BindTextureImage( target, rawIm );

	SetTexParam( target, GL_TEXTURE_WRAP_S, GL_REPEAT );
    SetTexParam( target, GL_TEXTURE_WRAP_T, GL_REPEAT );
    SetTexParam( target, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    SetTexParam( target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	LOG_INFO("Loaded texture {}", name);
	
	return rawIm.id;
}


