<template>
    <div id="pdp">
        <div class="col-xs-12 col-md-7">
            <carousel :images="carouselImages"></carousel>
        </div>

        <div class="col-xs-12 col-md-5">
            <h2>
                {{ product.displayName }}
            </h2>

            <p class="description">
                {{ product.description }}
            </p>

            <div class="selection-wrapper jumbotron">
                <div class="pdp-sizes">
                    <p class="pdp-chose-text">Size: </p>
                    <div class="pdp-inputs" v-for="size in sizes" :key="size">
                        <input type="radio" v-model="chosenSize" name="selectsize" v-bind:value="size" /> <span class="pdp-chose">{{ size }}</span>
                    </div>
                </div>
                <div class="pdp-colors">
                    <p class="pdp-chose-text">Color: </p>
                    <div class="pdp-inputs" v-for="color in colors" :key="color">
                        <input :disabled="colorsForCurrentSize.find(e => e == color) != color"  type="radio" v-model="chosenColor" name="selectColor" v-bind:value="color" /> <span class="pdp-chose">{{ color }}</span>
                    </div>
                </div>
            </div>

            <div class="checkout-variant" v-if="currentVariant != null">
                <h3 class="col-xs-12 col-sm-7 col-md-6">{{ currentVariant.priceFormatted }}</h3>
                <div class="col-xs-5 col-sm-6 col-md-6">
                    <button @click="add(currentVariant.code)" type="button" class="btn btn-primary btn-md">
                        <i class="fas fa-shopping-cart"></i>ADD TO CART
                    </button>
                </div>
            </div>
        </div>

    </div>
</template>

<script>
    import $ from 'jquery'
    import { EventBus } from '../event-bus.js';

    export default {       
        data() {
            return {
                variants: window.variantsPDP,
                product: window.productPDP,
                chosenColor: '',
                chosenSize: '',
                sizes: [],
                colors: [],
                currentVariant: null,
                carouselImages: [],
                colorsForCurrentSize: [],
            }
        },
        mounted() {
            this.initVariants();
        },
        watch: {
            chosenColor(newValue) {
                this.currentVariant = this.getVariant(this.chosenSize, newValue);
                this.initCarousel();
            },

            chosenSize(newValue) {
                this.currentVariant = this.getVariant(newValue, this.chosenColor);
                this.colorsForCurrentSize = [];
                this.getVariantsBySize(newValue).forEach(val => this.colorsForCurrentSize.push(val.color));
                this.initCarousel();
            }
        },
        methods: {
            initVariants() {
                let sizesDict = {}, colorsDict = {};
                this.variants.forEach(x => {
                    sizesDict[x.size] = 1;
                    colorsDict[x.color] = 1;
                });
                this.sizes = Object.keys(sizesDict);
                this.colors = Object.keys(colorsDict);
            },

            initCarousel() {
                if (this.currentVariant != null)
                    this.carouselImages = this.currentVariant.images;
                else
                    this.carouselImages = this.product.images;
            },

            add(code) {
                $.post({
                    url : "/api/ShoppingCartApi/AddItemToCart",
                    data: {
                        code : code,
                        quantity : 1
                    },
                    success: function (data) {
                        console.log('Quantity:' + data.miniCart.Quantity);
                    },
                    error: function () {

                        console.log('Carlos')
                    }
                });
                EventBus.$emit('i-changed', 1);
            },

            getVariant(size, color) {
                var variant = this.variants.filter(v => v.color == color && v.size == size)[0];

                return variant;
            },

            getVariantsBySize(size) {
                var toRet = this.variants.filter(v => v.size == size);

                return toRet;
            }
        },
        created: function () {
            this.initCarousel();
        },
    }
</script>