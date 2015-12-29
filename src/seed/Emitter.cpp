#include "Emitter.h"
#include "onut.h"

namespace seed
{
    Emitter::Emitter()
    {
        m_blend = onut::SpriteBatch::eBlendMode::PreMultiplied;
        m_filter = onut::SpriteBatch::eFiltering::Linear;
    }

    Emitter::~Emitter()
    {

    }

    void Emitter::Init(const string& in_fxName)
    {
        m_fxName = in_fxName;
    }

    void Emitter::Update()
    {
        Node::Update();
    }

    void Emitter::Render(Matrix* in_parentMatrix)
    {
        if (!m_visible)
        {
            return;
        }

        // generate our matrix
        Matrix transform = Matrix::Identity;
        transform *= Matrix::CreateScale(m_scale.get().x, m_scale.get().y, 1.f);
        transform *= Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));
        transform *= Matrix::CreateTranslation(m_position.get().x, m_position.get().y, 0);

        if (in_parentMatrix)
        {
            transform = transform * *in_parentMatrix;
        }

        // render bg children
        RenderChildren(m_bgChildren, &transform);

        // render ourself
        OSpriteBatch->changeBlendMode(m_blend);
        OSpriteBatch->changeFiltering(m_filter);
        m_emitter.setTransform(transform.Translation());
        m_emitter.render();

        // render fg children
        RenderChildren(m_fgChildren, &transform);
    }

    void Emitter::Start()
    {
        m_emitter = OEmitPFX(m_fxName.c_str(), Vector3());
        m_emitter.setRenderEnabled(false);
    }

    void Emitter::Stop()
    {
        m_emitter.stop();
    }

    void Emitter::SetFilter(onut::SpriteBatch::eFiltering in_filter)
    {
        m_filter = in_filter;
    }

    void Emitter::SetBlend(onut::SpriteBatch::eBlendMode in_blend)
    {
        m_blend = in_blend;
    }
}
