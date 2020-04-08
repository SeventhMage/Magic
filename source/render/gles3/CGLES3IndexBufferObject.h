#ifndef _MAGIC_C_GLES3INDEXBUFFEROBJECT_H_
#define _MAGIC_C_GLES3INDEXBUFFEROBJECT_H_

namespace magic
{
		class CGLES3IndexBufferObject : public IBufferObject
		{
		public:
			CGLES3IndexBufferObject(void *indices, GLsizei idsCount, GLenum idsType, GLenum mode, GLenum usage);
			virtual ~CGLES3IndexBufferObject();

			virtual void Bind();
			virtual void UnBind();

			virtual void BufferData(void *indices, int idsSize);
			virtual void BufferSubData(void *data, int size, int offset);
			virtual uint GetHandle() { return m_IBO; }
			virtual uint GetHandle() const { return m_IBO; }

			//GPUBufferType GetBufferType(){ return GBT_INDEX; };
			GLenum GetGPUBufferMode() { return m_gpuBufferMode; }
			GLenum GetGPUBufferUsage() { return m_gpuBufferUsage; }
			int GetIndicesNum() { return m_uIndicesNum; }						
			GLenum GetIndexType() { return m_idsType; }
		private:
			uint m_IBO;
			GLenum m_gpuBufferMode;
			GLenum m_gpuBufferUsage;
			GLenum m_idsType;
			GLsizei m_uIndicesNum;
		};
}

#endif