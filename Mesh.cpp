#include "main.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Debug.h"
#include "Shader.h"
#include "Application.h"

bool Mesh::SetupMesh() {

	HRESULT hr;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = UINT(sizeof(VERTEX_3D) * Vertices.size());
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &Vertices[0];

	hr = Renderer::GetDevice()->CreateBuffer(&vbd, &initData, &VertexBuffer);
	if (FAILED(hr))
		return false;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(UINT) * UINT(Indices.size());
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	initData.pSysMem = &Indices[0];

	hr = Renderer::GetDevice()->CreateBuffer(&ibd, &initData, &IndexBuffer);
	if (FAILED(hr))
		return false;

	D3D11_BUFFER_DESC cbd;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(col);
	cbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;

	initData.pSysMem = &col[0];

	hr = Renderer::GetDevice()->CreateBuffer(&cbd, &initData, &ColorBuffer);
	if (FAILED(hr))
		return false;

	return true;
}

void Mesh::CreateComputeResource() {

	HRESULT hr;

	// Buffer
	//hr = Renderer::CreateStructuredBuffer_DYN(sizeof(DEFORM_VERTEX), (UINT)mDeformVertex.size(), nullptr, &mpBuf);
	//assert(SUCCEEDED(hr));
	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(COMPUTEMATRIX), (UINT)Vertices.size(), nullptr, &mpBoneBuf);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateStructuredBuffer_DYN(sizeof(VERTEX_3D), (UINT)Vertices.size(), nullptr, &mpVerticesBuf);
	assert(SUCCEEDED(hr));

	/*hr = Renderer::CreateBufferSRV(mpBuf, &mpBufSRV);
	assert(SUCCEEDED(hr));*/
	hr = Renderer::CreateBufferSRV(mpBoneBuf, &mpBoneBufSRV);
	assert(SUCCEEDED(hr));
	hr = Renderer::CreateBufferSRV(mpVerticesBuf, &mpVerticesBufSRV);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateStructuredBuffer(sizeof(VERTEX_3D), (UINT)Vertices.size(), nullptr, &resultbuffer);
	assert(SUCCEEDED(hr));

	hr = Renderer::CreateBufferUAV(resultbuffer, &mpBufUAV);
	assert(SUCCEEDED(hr));

}

void Mesh::Update() {

	if (Application::GetUsingGPU()) {
		// Fill Data
		{
			//// Fill DeformVertex
			//D3D11_MAPPED_SUBRESOURCE subRes;
			//Renderer::GetDeviceContext()->Map(mpBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
			//DEFORM_VERTEX* pBufType = (DEFORM_VERTEX*)subRes.pData;
			//for (unsigned int v = 0; v < mDeformVertex.size(); v++) {
			//	pBufType[v] = mDeformVertex[v];
			//}
			//Renderer::GetDeviceContext()->Unmap(mpBuf, 0);

			// Fill COMPUTEMATRIX
			D3D11_MAPPED_SUBRESOURCE subRes_1;
			Renderer::GetDeviceContext()->Map(mpBoneBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes_1);
			COMPUTEMATRIX* pBufType_cm = (COMPUTEMATRIX*)subRes_1.pData;
			for (unsigned int v = 0; v < Vertices.size(); v++) {
				DEFORM_VERTEX* deform = &mDeformVertex[v];
				aiMatrix4x4 matrix[4];


				std::string* str = deform->mBoneName;
				matrix[0] = mBone[str[0]].mMatrix;
				matrix[1] = mBone[str[1]].mMatrix;
				matrix[2] = mBone[str[2]].mMatrix;
				matrix[3] = mBone[str[3]].mMatrix;

				{
					pBufType_cm[v].outMatrix.a1 = matrix[0].a1 * deform->mBoneWeight[0] + matrix[1].a1 * deform->mBoneWeight[1] + matrix[2].a1 * deform->mBoneWeight[2] + matrix[3].a1 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.a2 = matrix[0].a2 * deform->mBoneWeight[0] + matrix[1].a2 * deform->mBoneWeight[1] + matrix[2].a2 * deform->mBoneWeight[2] + matrix[3].a2 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.a3 = matrix[0].a3 * deform->mBoneWeight[0] + matrix[1].a3 * deform->mBoneWeight[1] + matrix[2].a3 * deform->mBoneWeight[2] + matrix[3].a3 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.a4 = matrix[0].a4 * deform->mBoneWeight[0] + matrix[1].a4 * deform->mBoneWeight[1] + matrix[2].a4 * deform->mBoneWeight[2] + matrix[3].a4 * deform->mBoneWeight[3];

					pBufType_cm[v].outMatrix.b1 = matrix[0].b1 * deform->mBoneWeight[0] + matrix[1].b1 * deform->mBoneWeight[1] + matrix[2].b1 * deform->mBoneWeight[2] + matrix[3].b1 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.b2 = matrix[0].b2 * deform->mBoneWeight[0] + matrix[1].b2 * deform->mBoneWeight[1] + matrix[2].b2 * deform->mBoneWeight[2] + matrix[3].b2 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.b3 = matrix[0].b3 * deform->mBoneWeight[0] + matrix[1].b3 * deform->mBoneWeight[1] + matrix[2].b3 * deform->mBoneWeight[2] + matrix[3].b3 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.b4 = matrix[0].b4 * deform->mBoneWeight[0] + matrix[1].b4 * deform->mBoneWeight[1] + matrix[2].b4 * deform->mBoneWeight[2] + matrix[3].b4 * deform->mBoneWeight[3];

					pBufType_cm[v].outMatrix.c1 = matrix[0].c1 * deform->mBoneWeight[0] + matrix[1].c1 * deform->mBoneWeight[1] + matrix[2].c1 * deform->mBoneWeight[2] + matrix[3].c1 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.c2 = matrix[0].c2 * deform->mBoneWeight[0] + matrix[1].c2 * deform->mBoneWeight[1] + matrix[2].c2 * deform->mBoneWeight[2] + matrix[3].c2 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.c3 = matrix[0].c3 * deform->mBoneWeight[0] + matrix[1].c3 * deform->mBoneWeight[1] + matrix[2].c3 * deform->mBoneWeight[2] + matrix[3].c3 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.c4 = matrix[0].c4 * deform->mBoneWeight[0] + matrix[1].c4 * deform->mBoneWeight[1] + matrix[2].c4 * deform->mBoneWeight[2] + matrix[3].c4 * deform->mBoneWeight[3];

					pBufType_cm[v].outMatrix.d1 = matrix[0].b1 * deform->mBoneWeight[0] + matrix[1].d1 * deform->mBoneWeight[1] + matrix[2].d1 * deform->mBoneWeight[2] + matrix[3].d1 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.d2 = matrix[0].b2 * deform->mBoneWeight[0] + matrix[1].d2 * deform->mBoneWeight[1] + matrix[2].d2 * deform->mBoneWeight[2] + matrix[3].d2 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.d3 = matrix[0].b3 * deform->mBoneWeight[0] + matrix[1].d3 * deform->mBoneWeight[1] + matrix[2].d3 * deform->mBoneWeight[2] + matrix[3].d3 * deform->mBoneWeight[3];
					pBufType_cm[v].outMatrix.d4 = matrix[0].b4 * deform->mBoneWeight[0] + matrix[1].d4 * deform->mBoneWeight[1] + matrix[2].d4 * deform->mBoneWeight[2] + matrix[3].d4 * deform->mBoneWeight[3];
				}

			}
			Renderer::GetDeviceContext()->Unmap(mpBoneBuf, 0);

			// Fill Vertex
			D3D11_MAPPED_SUBRESOURCE subRes_2;
			Renderer::GetDeviceContext()->Map(mpVerticesBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes_2);
			VERTEX_3D* pBufType_vtx = (VERTEX_3D*)subRes_2.pData;
			for (unsigned int v = 0; v < Vertices.size(); v++) {
				pBufType_vtx[v] = Vertices[v];
			}
			Renderer::GetDeviceContext()->Unmap(mpVerticesBuf, 0);
		}

		ID3D11ShaderResourceView* pSRVs[2] = { mpBoneBufSRV, mpVerticesBufSRV };
		Renderer::GetDeviceContext()->CSSetShaderResources(0, 2, pSRVs);
		Renderer::GetDeviceContext()->CSSetShader(Shader::GetComputeShaderArray()[1], nullptr, 0);
		Renderer::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &mpBufUAV, nullptr);

		Renderer::GetDeviceContext()->Dispatch(128, 1, 1);


		ID3D11Buffer* pBufDbg;
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(desc));
		resultbuffer->GetDesc(&desc);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;
		Renderer::GetDevice()->CreateBuffer(&desc, nullptr, &pBufDbg);
		Renderer::GetDeviceContext()->CopyResource(pBufDbg, resultbuffer);

		// CopyResult
		{
			D3D11_MAPPED_SUBRESOURCE subRes;
			VERTEX_3D* pBufType;
			Renderer::GetDeviceContext()->Map(pBufDbg, 0, D3D11_MAP_READ, 0, &subRes);
			pBufType = (VERTEX_3D*)subRes.pData;

			{
				D3D11_MAPPED_SUBRESOURCE ms;
				Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
				VERTEX_3D* vertex = (VERTEX_3D*)ms.pData;

				for (unsigned int v = 0; v < Vertices.size(); v++) {
					vertex[v].Position = pBufType[v].Position;
					vertex[v].Normal = pBufType[v].Normal;
					vertex[v].TexCoord = pBufType[v].TexCoord;
					vertex[v].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
				}
				Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);
			}
			Renderer::GetDeviceContext()->Unmap(pBufDbg, 0);
			pBufDbg->Release();
		}
	}

	else {

		D3D11_MAPPED_SUBRESOURCE mse;
		Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mse);
		VERTEX_3D* vertex2 = (VERTEX_3D*)mse.pData;

		for (unsigned int v = 0; v < Vertices.size(); v++) {

			DEFORM_VERTEX* deform = &mDeformVertex[v];

			aiMatrix4x4 outMatrix;
			aiMatrix4x4 matrix[4];

			std::string* str = deform->mBoneName;

			matrix[0] = mBone[str[0]].mMatrix;
			matrix[1] = mBone[str[1]].mMatrix;
			matrix[2] = mBone[str[2]].mMatrix;
			matrix[3] = mBone[str[3]].mMatrix;

			{
				outMatrix.a1 = matrix[0].a1 * deform->mBoneWeight[0] + matrix[1].a1 * deform->mBoneWeight[1] + matrix[2].a1 * deform->mBoneWeight[2] + matrix[3].a1 * deform->mBoneWeight[3];
				outMatrix.a2 = matrix[0].a2 * deform->mBoneWeight[0] + matrix[1].a2 * deform->mBoneWeight[1] + matrix[2].a2 * deform->mBoneWeight[2] + matrix[3].a2 * deform->mBoneWeight[3];
				outMatrix.a3 = matrix[0].a3 * deform->mBoneWeight[0] + matrix[1].a3 * deform->mBoneWeight[1] + matrix[2].a3 * deform->mBoneWeight[2] + matrix[3].a3 * deform->mBoneWeight[3];
				outMatrix.a4 = matrix[0].a4 * deform->mBoneWeight[0] + matrix[1].a4 * deform->mBoneWeight[1] + matrix[2].a4 * deform->mBoneWeight[2] + matrix[3].a4 * deform->mBoneWeight[3];

				outMatrix.b1 = matrix[0].b1 * deform->mBoneWeight[0] + matrix[1].b1 * deform->mBoneWeight[1] + matrix[2].b1 * deform->mBoneWeight[2] + matrix[3].b1 * deform->mBoneWeight[3];
				outMatrix.b2 = matrix[0].b2 * deform->mBoneWeight[0] + matrix[1].b2 * deform->mBoneWeight[1] + matrix[2].b2 * deform->mBoneWeight[2] + matrix[3].b2 * deform->mBoneWeight[3];
				outMatrix.b3 = matrix[0].b3 * deform->mBoneWeight[0] + matrix[1].b3 * deform->mBoneWeight[1] + matrix[2].b3 * deform->mBoneWeight[2] + matrix[3].b3 * deform->mBoneWeight[3];
				outMatrix.b4 = matrix[0].b4 * deform->mBoneWeight[0] + matrix[1].b4 * deform->mBoneWeight[1] + matrix[2].b4 * deform->mBoneWeight[2] + matrix[3].b4 * deform->mBoneWeight[3];

				outMatrix.c1 = matrix[0].c1 * deform->mBoneWeight[0] + matrix[1].c1 * deform->mBoneWeight[1] + matrix[2].c1 * deform->mBoneWeight[2] + matrix[3].c1 * deform->mBoneWeight[3];
				outMatrix.c2 = matrix[0].c2 * deform->mBoneWeight[0] + matrix[1].c2 * deform->mBoneWeight[1] + matrix[2].c2 * deform->mBoneWeight[2] + matrix[3].c2 * deform->mBoneWeight[3];
				outMatrix.c3 = matrix[0].c3 * deform->mBoneWeight[0] + matrix[1].c3 * deform->mBoneWeight[1] + matrix[2].c3 * deform->mBoneWeight[2] + matrix[3].c3 * deform->mBoneWeight[3];
				outMatrix.c4 = matrix[0].c4 * deform->mBoneWeight[0] + matrix[1].c4 * deform->mBoneWeight[1] + matrix[2].c4 * deform->mBoneWeight[2] + matrix[3].c4 * deform->mBoneWeight[3];

				outMatrix.d1 = matrix[0].b1 * deform->mBoneWeight[0] + matrix[1].d1 * deform->mBoneWeight[1] + matrix[2].d1 * deform->mBoneWeight[2] + matrix[3].d1 * deform->mBoneWeight[3];
				outMatrix.d2 = matrix[0].b2 * deform->mBoneWeight[0] + matrix[1].d2 * deform->mBoneWeight[1] + matrix[2].d2 * deform->mBoneWeight[2] + matrix[3].d2 * deform->mBoneWeight[3];
				outMatrix.d3 = matrix[0].b3 * deform->mBoneWeight[0] + matrix[1].d3 * deform->mBoneWeight[1] + matrix[2].d3 * deform->mBoneWeight[2] + matrix[3].d3 * deform->mBoneWeight[3];
				outMatrix.d4 = matrix[0].b4 * deform->mBoneWeight[0] + matrix[1].d4 * deform->mBoneWeight[1] + matrix[2].d4 * deform->mBoneWeight[2] + matrix[3].d4 * deform->mBoneWeight[3];
			}

			deform->Position.x = Vertices[v].Position.x;
			deform->Position.y = Vertices[v].Position.y;
			deform->Position.z = Vertices[v].Position.z;

			deform->Position *= outMatrix;

			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deform->Normal.x = Vertices[v].Normal.x;
			deform->Normal.y = Vertices[v].Normal.y;
			deform->Normal.z = Vertices[v].Normal.z;
			deform->Normal *= outMatrix;

			vertex2[v].Position.x = deform->Position.x;
			vertex2[v].Position.y = deform->Position.y;
			vertex2[v].Position.z = deform->Position.z;

			vertex2[v].Normal.x = deform->Normal.x;
			vertex2[v].Normal.y = deform->Normal.y;
			vertex2[v].Normal.z = deform->Normal.z;

			vertex2[v].TexCoord.x = Vertices[v].TexCoord.x;
			vertex2[v].TexCoord.y = Vertices[v].TexCoord.y;

			vertex2[v].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
		}

		Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);
	}
}

void Mesh::Draw(){
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(ColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	float* col = (float*)msr.pData;
	col[0] = this->col[0];
	col[1] = this->col[1];
	col[2] = this->col[2];
	col[3] = this->col[3];
	Renderer::GetDeviceContext()->Unmap(ColorBuffer, 0);

	Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &ColorBuffer);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	if (!Renderer::mLineMode) {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	else {
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	}

	Renderer::SetMaterial(Material);

	Renderer::GetDeviceContext()->DrawIndexed((UINT)Indices.size(), 0, 0);
}

void Mesh::Close() {

	VertexBuffer->Release();
	IndexBuffer->Release();
	ColorBuffer->Release();

	Vertices.clear();
	Vertices.shrink_to_fit();

	Indices.clear();
	Indices.shrink_to_fit();

	Textures.clear();
	Textures.shrink_to_fit();

	mDeformVertex.clear();
	mDeformVertex.shrink_to_fit();

	mBone.clear();

}

void Mesh::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix) {

	BONE* bone = &mBone[node->mName.C_Str()];

	aiMatrix4x4 world;
	world = matrix;
	world *= bone->mAnimationMatrix;

	bone->mMatrix = world;
	bone->mMatrix *= bone->mOffsetMatirx;

	for (unsigned int n = 0; n < node->mNumChildren; n++) {
		UpdateBoneMatrix(node->mChildren[n], world);
	}
}