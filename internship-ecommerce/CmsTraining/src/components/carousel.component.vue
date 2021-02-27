<template>
    <div>
        <slick id="c1" ref="c1" :options="slickOptions">
            <div class="vue-slick-main"  v-for="img in images" :key="img">
                <img :src="img" />
            </div>
        </slick>
        <slick id="c2" ref="c2" :options="slickOptions2">
            <div class="vue-slick-thumbnails" v-for="img in images" :key="img">
                <img :src="img" />
            </div>
        </slick>
    </div>
</template>

<script>
    import Slick from "vue-slick";

    export default {
        props: ['images'],
        components: { Slick },
        watch: {
            images: function() {
                let currIndex = this.$refs.c1.currentSlide()
                this.$refs.c1.destroy()
                this.$nextTick(() => {
                    this.$refs.c1.create()
                    this.$refs.c1.goTo(currIndex, true)
                });
                let currIndex2 = this.$refs.c2.currentSlide()
                this.$refs.c2.destroy()
                this.$nextTick(() => {
                    this.$refs.c2.create()
                    this.$refs.c2.goTo(currIndex2, true)
                })
            }
        },
        computed: {
            slickOptions() {
                return {
                    slidesToShow: 1,
                    slidesToScroll: 1,
                    arrows: false,
                    fade: true,
                    adaptiveHeight: true,
                    asNavFor: "#c2"
                }
            },
            slickOptions2() {
                return {
                    slidesToShow: 3,
                    slidesToScroll: 1,
                    dots: false,
                    autoplay: true,
                    speed: 2000,
                    infinite: true,
                    cssEase: "linear",
                    focusOnSelect: true,
                    asNavFor: "#c1",
                    draggable: false,
                    adaptiveHeight: true
                }
            }
        }
    }
</script>
