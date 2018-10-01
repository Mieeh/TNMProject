#pragma once

#include<vector>
#include<string>

namespace bear { namespace graphics {

	static float animation_tick_constant = .2f;

	struct AnimatedKeyframe {
		std::string m_TextureName; // Texture name for this keyframe
	};
	
	struct AnimatedSprite {
		// Keyframe data
		unsigned short int m_CurrentKeyframeIndex;
		std::vector<AnimatedKeyframe> m_Keyframes;
		// Keyframe control data
		unsigned short int m_TickBreak;
		unsigned short int m_CurrentTick;

		// Current keyframe texture name
		std::string m_CurrentTextureName;

		// Play data
		bool m_IsPlaying;
		bool m_IsLooping;
		bool m_DonePlaying;

		// Constructor
		AnimatedSprite();

		// Adds a new keyframe at the back of the animation
		void addKeyframe(AnimatedKeyframe& a_Keyframe);
		// start the animation
		void play();
		// sto pthe animation
		void stop();
		// forwards the animation
		void update(float a_Delta);
		// resets to first keyframe in the animation
		void reset();
	};

} }