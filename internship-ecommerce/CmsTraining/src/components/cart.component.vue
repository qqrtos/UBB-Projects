<template>
    <div>
        <div class="empty-cart-txt" v-if="total==='0$' || total==='0.00$'">
            Your shopping cart is empty, you can buy stuff at <a :href="createUrl(link)">our products page</a>
        </div>
        <div v-else>
            <div class="divBorderRight col col-xs-12 col-sm-12 col-md-8 col-lg-8 ">
                <div v-for="(product, index) in products" :key="product.code">
                    <div class="row" style="border-bottom: 1px solid #e8e8e8; padding-bottom:2rem; padding-top:2rem;">
                        <div class="col-xs-12 col-sm-4 col-md-2 ">
                            <img class="cart-img" :src="product.image">
                        </div>
                        <div>
                            <div class="col-xs-12 col-sm-4 col-md-6 itemDetails">
                                <span class="itemTitle">{{product.displayName}} </span><br>
                                Size: {{product.size }} <br>
                                Color: {{product.color }}<br>
                                Price: {{product.placedPriceFormatted}}

                            </div>
                            <div class="col-xs-12 col-sm-4 col-md-4 ">
                                <ValidationObserver ref="observer">
                                    <ValidationProvider rules="between:1,100" v-slot="{ errors }">
                                        <div class="row">
                                            <div class="col-xs-10 col-md-10">
                                                <input name="Quantity" :placeholder="product.quantity" size="1" v-model="quantityInput[product.code]" class="QuantityInput" />
                                            </div>
                                            <div class="col-xs-1 col-md-1">
                                                <button class="deleteButton" type="button" @click="delItem(product); getCart()"><i class="fa fa-times" aria-hidden="true"></i></button>
                                            </div>
                                        </div>
                                        <div><span>{{errors[0]}}</span></div>
                                        <div class="row">
                                            <div class="col-xs-10 col-md-10">
                                                <button class="cartbutton" type="submit" @click="changeQuantity(product, index); getCart()" :disabled="errors.length > 0">change</button>
                                            </div>

                                        </div>
                                    </ValidationProvider>
                                </ValidationObserver>
                            </div>

                        </div>

                    </div>
                </div>
            </div>

            <div class="col-xs-12 col-sm-12 col-md-4 col-lg-4" style="padding-left:2.5em; ">
                <div class="row">
                    <div class="col-xs-12 col-sm-12 col-md-12 col-lg-12" style="padding-top: 0px;">
                        <h3 class="cart" style="margin-top: 0px;">Cart summary</h3>
                    </div>
                </div>
                <div class="row cart_section">
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6" style="padding-top: 2em;">
                        Subtotal:
                    </div>
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6" style="padding-top: 2em;">
                        <b> {{total}}</b>
                    </div>
                </div>
                <div class="row cart_section">
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        <span style="color:#C9BB7A" class="summaryTitles">Discount:</span>
                    </div>
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        <b>0$</b>
                    </div>
                </div>
                <div class="row cart_section">
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        Shipping:
                    </div>
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        <b>0$</b>
                    </div>
                </div>
                <div class="row cart_section">
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        Tax:
                    </div>
                    <div class="col-xs-6 col-sm-6 col-md-4 col-lg-6">
                        <b>0$</b>
                    </div>
                </div>
                <div class="row cart_section">
                    <hr class="cart_hr">
                </div>
                <div class="row cart_section" style="padding-bottom: 2em;">
                    <div class="col-xs-6 col-sm-6 col-md-4">
                        <h3 class="product_details">Total:</h3>
                    </div>
                    <div class="col-xs-6 col-sm-6 col-md-4">
                        <h3 class="product_details" style="color: black; font-weight: bolder;"> {{total}}</h3>
                    </div>
                </div>
                <div class="row justify-content-end">
                    <div class="col-md-8 " style="padding-top: 2em;">

                        <button type="button" class="btn btn-primary btn-lg button_checkout"><b>CHECKOUT</b></button>
                    </div>

                </div>
            </div>
        </div>
    </div>

</template>

<script> 
    import $ from 'jquery'
    import { EventBus } from '../event-bus.js';

    export default {
        name: 'app',
        data() {
            return {
                products: window.productsLineItems,
                total: window.total,
                link: window.link,
                quantityInput: {}
            };
        },

       
        methods: {
            changeQuantity(prod, index) {
                let self = this;
                $.post({
                    url: "/api/ShoppingCartApi/UpdateQuantity",
                    data: {
                        code: prod.code,
                        quantity: this.quantityInput[prod.code]
                    },
                    success: function (data) {
                        let quantityDifference = self.quantityInput[prod.code] - prod.quantity;
                        self.products[index].quantity = data.miniCart.Quantity;
                        EventBus.$emit('i-changed', quantityDifference);
                    },
                    error: function () {
                        console.log('Carlos')
                    }
                });
            },
            createUrl(url) {
                return window.baseUrl + url.substring(1);
            },
            getCart() {
                const self = this;
                setTimeout(function () {
                    $.get({
                        url: "/api/ShoppingCartApi/GetCartTotal",
                        data: {
                        },
                        success: function (data) {
                            self.total = data;
                        },
                        error: function () {
                            console.log('Carlos')
                        }
                    });
                }, 100);
                
            },

            delItem(prod) {
                const self = this;
                $.post({
                    url: "/api/ShoppingCartApi/UpdateQuantity",
                    data: {
                        code: prod.code,
                        quantity: 0
                    },
                    success: function () {
                        let result = self.products.filter(el => el.code != prod.code);
                        self.products = result;
                        EventBus.$emit('i-changed', (-1)*prod.quantity);
                    },
                    error: function () {
                        console.log('Carlos')
                    }
                });
            },
        }
    }
</script>